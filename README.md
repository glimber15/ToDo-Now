# Todo CLI
> A todo app which lives im your project. It's kinda like your TODO.md but more cli-y and only show you whats is important.

## Usage
`"usage                      tsk <action> <params...>\n\n"
"actions:\n"
"  init                     Initialize tasks in project dir\n"
"  add 'task title'         Add a task\n"
"  desc id 'description'    Add description to a task\n"
"  show                     Show tasks pending\n"
"  show -c                  Show completed tasks also\n"
"  tick id                  Complete/toggle a task\n"
"  edit id 'new title'      Edit a task title\n"
"  del id                   Delete a task\n"
"  kaboom                   Uninitaialize tasks\n"`

> Also using `tsk show >> todo.txt` can give you a task file
