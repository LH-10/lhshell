# LHShell

**LHShell** is a simple Unix shell written in C for Linux. It was built to understand how shells work and how processes are created and executed in Unix systems.

### Features

* Run commands using the `fork()` + `exec()` model
* Supports `cd`
* Shows the current working directory after changing directories
* Colored terminal output
* Works for unix based systems

### Build & Run

Clone the repository and run:

```bash
make
```

This builds the shell inside the `build/` directory.

Then run:

```bash
./build/lhshell
```

### How it works

LHShell reads a command, creates a child process using `fork()`, and uses `exec()` to run the command. The parent process waits for the child to finish before displaying the prompt again.

The `cd` command is handled directly by the shell since changing directories in a child process would not affect the shell's working directory.

### To exit Shell 
Press `Ctrl-D` or `Ctrl-Z` 

