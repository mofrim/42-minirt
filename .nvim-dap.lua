local dap = require 'dap'

dap.adapters.gdb = {
	type = 'executable',
	command = 'gdb',
 args = { "--interpreter=dap", "--eval-command", "set print pretty on" }
}

print("workspaceFolder = ${workspaceFolder}")

dap.configurations.c = {
	{
		name = 'Launch',
		type = 'gdb',
		request = 'launch',
		program = "./minirt",
		args = "./rtfiles/just_one_hyper.rt",
		cwd = '${workspaceFolder}',
		stopAtBeginningOfMainSubprogram = false,
	},
}
