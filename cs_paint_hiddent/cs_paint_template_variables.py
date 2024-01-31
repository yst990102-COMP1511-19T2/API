import os
import subprocess

import sys; sys.path += ['..', '../..']
try:
    from scripts.config import variables
    course_number = variables['course_number']
    public_html_session_directory = variables['public_html_session_directory']
except ImportError:
    course_number = '1511'
    public_html_session_directory = "/web/cs1511/19T2"

FRAGMENT = """
<div class="card">

  <div class="card-header" id="headingOne">
    <h4 class="panel-title">
      <a class="btn btn-link" id="#{name_link}" href="#{name_link}" data-toggle="collapse" data-target="#{hash}_collapse" aria-expanded="false" aria-controls="{hash}_collapse">
        Show Test-Case: {name}
      </a>
      <!--
      <button class="btn btn-link" data-toggle="collapse" data-target="#{hash}_collapse" aria-expanded="false" aria-controls="{hash}_collapse">
          Show Test-Case: {name}
      </button>
      -->
    </h4>
  </div>

  <div id="{hash}_collapse" class="collapse" aria-labelledby="{hash}_collapse" data-parent="#{hash}_collapse">
    <div class="card-body thinner">
      <ul class="nav nav-tabs">
        <li class="show"><a data-toggle="tab" class="nav-link visible-tab active" href="#{hash}_normalin">Input</a></li>
        <li class="show"><a data-toggle="tab" class="nav-link visible-tab" href="#{hash}_rawin">Raw Input</a></li>
      </ul>

      <div class="tab-content">
        <div id="{hash}_normalin" class="tab-pane active show">
          <table class="table">
            <thead><tr><th class="borderless">Command</th><th class="borderless">Meaning</th></tr></thead>
            <tbody>
            {input_rows}
            </tbody>
          </table>
        </div>
        <div id="{hash}_rawin" class="tab-pane">
          <table class="table">
            <thead><tr><th class="borderless">Raw Input</th></tr></thead>
            <tbody>
              <tr><td><pre>{plain_input}</pre></td></tr>
            </tbody>
          </table>
        </div>
      </div>

      <!--
      <ul class="nav nav-tabs">
        <li class="show"><a data-toggle="tab" class="nav-link" href="#{hash}_normalin">Input</a></li>
      </ul>
      <div class="tab-content">
      <table class="table">
        <thead><tr><th class="borderless">Command</th><th class="borderless">Meaning</th></tr></thead>
        <tbody>
        {input_rows}
        -->
        <!--
        <tr>
          <td><pre>{normal_input}</pre></td>
          <td style="padding-top:15px">{nice_input}</td>
        </tr>
        -->
        <!--
        </tbody>
      </table>
      </div>
      -->






      <!-- Start Output -->
      <div class="tab-content">
        <ul class="nav nav-tabs">
          <li class="show"><a data-toggle="tab" class="nav-link visible-tab active" href="#{hash}_normalout">Output</a></li>
          <li class="show"><a data-toggle="tab" class="nav-link visible-tab" href="#{hash}_niceout">Output (stylized)</a></li>
        </ul>
        <div id="{hash}_normalout" class="tab-pane active show">
          <pre class="inverted-color command_line">{normal_output}</pre>
        </div>
        <div id="{hash}_niceout" class="tab-pane">
          <pre class="cspaint-nice inverted-color command_line">{nice_output}</pre>
          <div class="alert alert-danger">
            <b>Your program should not produce this output, <code>{course_number} canvas</code> will.</b>
          </div>
        </div>
      </div>
      <!-- End Output -->
    </div>
  </div>
</div>
"""

CS_PAINT_DIR = os.path.dirname(os.path.realpath(__file__))

def cache(f):
    from functools import wraps
    import pickle
    pickle_path = os.path.join(CS_PAINT_DIR, 'cache.pickle')
    if os.path.exists(pickle_path):
        p = pickle.load(open(pickle_path, 'rb'))
    else:
        p = {}
    @wraps(f)
    def wrapper(*args, **kwargs):
        if (*args,) in p:
            return p[(*args,)]
        val = f(*args, **kwargs)
        if hasattr(os, 'cs_paint_cache') and (*args,) not in p:
            print(f"... cached {f.__name__} call with args: {args}")
            p[(*args,)] = val
            with open(pickle_path, 'wb') as pickle_file:
                pickle.dump(p, pickle_file)
            if 'name' in kwargs:
                demo_path = os.path.join(CS_PAINT_DIR, 'demos')
                os.makedirs(demo_path, exist_ok=True)
                name = kwargs['name'].lower().replace(' ', '_') + '.in'
                demo_file_path =os.path.join(demo_path, name)
                if not os.path.exists(demo_file_path):
                    with open(demo_file_path, 'w') as demo_file:
                        demo_file.write(name)
        return val

    return wrapper


def cmd_to_plain_english(commands):
    ENGLISH_COMMANDS = {
        '1': "DRAW LINE",
        '2': "FILL RECTANGLE",
        '4': "COPY RECTANGLE",
    }
    ENGLISH_SHADES = {
        '0': "Black",
        '1': "Dark",
        '2': "Grey",
        '3': "Light",
        '4': "White",
    }
    nice = []
    for command in commands:
        try:
            command = list(filter(len, command.strip().split(' ')))
            text = ""
            if command[0] in ['1', '2', '4']:
                text += ENGLISH_COMMANDS[command[0]]
                text += f" starting at (row {command[1]}, col {command[2]})"
                text += f" until (row {command[3]}, col {command[4]})"
                if command[0] == '4':
                    text += f"; PASTE STARTING AT (row {command[5]}, col {command[6]})"
            if command[0] == '3':
                shade_name = ENGLISH_SHADES[command[1]]
                text += f"USE BRUSH WITH SHADE {shade_name} (code: {command[1]})"
            if command[0] == '5':
                text += f"USE 3x3 BRUSH THAT ADDS SHADES {', '.join(command[1:])}"
            try:
                start_row, start_col, end_row, end_col = map(int, command[1:])
                row_dist = abs(end_row - start_row)
                col_dist = abs(end_col - start_col)
                if command[0] == '1' and row_dist == col_dist:
                    if row_dist > 0:
                        text += " DIAGONALLY"
                    else:
                        text += " (A POINT)"
                elif command[0] == '1' and row_dist > 0 and col_dist == 0:
                    text += " VERTICALLY"
                elif command[0] == '1' and col_dist > 0 and row_dist == 0:
                    text += " HORIZONTALLY"

            except:
                pass
            text += '.'
        except IndexError:
            text = "Could not create English text - invalid commands!"
        nice.append(text)

    return nice


def filter_canvas_output(output):
    output_lines = output.split('\n')
    new_output = []

    for line in output_lines:
       if not any([line.startswith(a) for a in ['Compiling', 'dcc']]):
            new_output.append(line)

    return '\n'.join(new_output)


@cache
def call_canvas(input_text, show_numbers, name=""):
    args = [
        os.path.join(CS_PAINT_DIR, 'canvas.sh'),
        os.path.join(CS_PAINT_DIR, 'hidden_solutions', 'paint.c'),
                "--disable-terminal-colors",
    ]
    if show_numbers:
        args += ['--show-numbers']

    return filter_canvas_output(subprocess.check_output(
        args,
        input = input_text.encode('utf-8'),
        env = dict(
            os.environ,
            LC_ALL = 'en_AU.UTF-8',
            LANG   = 'en_AU.UTF-8',
        ),
    ).decode('utf-8').rstrip())


def show_cs_paint_example(name, commands):
    name_hash = str(hash(name))[:10]
    normal_input = '\n'.join(commands)
    nice_input = '\n'.join(cmd_to_plain_english(commands))

    input_rows = '\n'.join([show_cs_paint_example_text_tr(command)
        for command in commands])

    normal_output = show_redirect(name) + '\n' + "<span class='output'>" + call_canvas(normal_input, True, name=name) + "</span>"
    nice_output = show_command(name) + "\n" + "<span class='output'>" + call_canvas(normal_input, False, name=name) + "</span>"
    return FRAGMENT.format(
        hash=name_hash,
        name=name,
        name_link=name.replace(" ", "_").lower(),
        normal_input="<span>" + normal_input + "</span>",
        plain_input=normal_input,
        normal_output=normal_output,
        nice_input=nice_input,
        nice_output=nice_output,
        input_rows=input_rows,
        course_number=course_number
    )


def show_summary(name, command, instruction, arguments, examples):
    examples_code = "\n".join([show_cs_paint_example_text_tr(x) for x in examples])
    return f"""
<div class="card">
  <div class="card-header">
    {name}: Summary
  </div>

  <div class="card-body thinner">
   <table class="table">
    <tr>
      <th style="border-top: 0"><b>Command</b></td> <td style="border-top: 0"> "{command}"</td>
    </tr>
    <tr>
      <td><b>Instruction</b></td> <td><code>{instruction}</code></td>
    </tr>
    <tr>
      <td><b>Inputs</b></td> <td><code>{arguments}</code></td>
    </tr>
    <tr>
      <td><b>Examples</b></td>
      <td>
          <table>
              <thead><tr><th class="borderless">Command</th><th class="borderless">Meaning</th></tr></thead>
              <tbody>
                  {examples_code}
              </tbody>
          </table>
      </td>
    </tr>
   </table>
  </div>
</div>
"""

def show_command(name):
    return f"""
<kbd class='inverted-color shell'>{course_number} canvas paint.c {public_html_session_directory}/cs_paint/demos/{name.lower().replace(' ', '_')}.in</kbd>
""".strip("\n")

def show_redirect(name):
    file_name = name.lower().replace(' ', '_')
    return f"""
<kbd class="inverted-color shell">dcc -o cs_paint paint.c</kbd>
<kbd class="inverted-color shell">./cs_paint < {public_html_session_directory}/cs_paint/demos/{file_name}.in</kbd>
""".strip("\n")
#" + name.lower().replace(' ', '_') + ".in</kbd>"

def show_cs_paint_example_output(name, commands):
    full_html = show_cs_paint_example(name, commands)
    middle = full_html.split('<!-- Start Output -->')[1].split('<!-- End Output -->')[0]
    return f"""
    <div class="card">
    <div class="card-header">{name}</div>
    <div class="card-body thinner">
    {middle}
    </div>
    </div>
    """


def show_cs_paint_example_text_tr(command):
    plain_english_cmd = cmd_to_plain_english([command])[0]
    #return f"<pre>{command}  // which means {plain_english_cmd}</pre>"
    return f"""
            <tr>
              <td style="vertical-align: middle"><pre style="margin: 0">{command}</pre></td>
              <td style="vertical-align: middle">{plain_english_cmd}</td>
            </tr>"""


def show_cs_paint_example_text(command):
    plain_english_cmd = cmd_to_plain_english([command])[0]
    #return f"<pre>{command}  // which means {plain_english_cmd}</pre>"
    return f"""
        <table class="table-borderless table">
          <thead>
            <tr>
              <td style="border-top: 0px"><b>Command</b></td>
              <td style="border-top: 0px"><b>Meaning</b></td>
            </tr>
          </thead>
          <tbody>
            <tr>
              <td><pre>{command}</pre></td>
              <td style="padding-top:15px">{plain_english_cmd}</td>
            </tr>
          </tbody>
        </table>"""

CS_PAINT_TEMPLATE_FUNCTIONS = {
    'show_cs_paint_example': show_cs_paint_example,
    'show_cs_paint_example_output': show_cs_paint_example_output,
    'show_cs_paint_example_text': show_cs_paint_example_text,
    'show_cs_paint_example_text_tr': show_cs_paint_example_text_tr,
    'show_summary': show_summary,
}
