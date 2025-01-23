# Windows system 

## Install WSL2 

1. Install Windows Terminal from Microsoft Store.

2. WSL2 
Run Termnial in administrator mode.
(Windows + S, search Terminal, Right-click to run in administrator mode.)
Type the following commands:
```
$ wsl —install 
$ wsl --set-default-version 2
```

3. Install Ubuntu Linux from Microsoft Store
ID: kus2024, PASSWD: kus2024

4. Check the WSL version 
```
$ wsl -l -v 
```
If version is 1, then try 
```
$ wsl --set-version Ubuntu 2
$ wsl -l -v 
```

## Install Python3

1. Update Ubuntu distribution
```
sudo apt update
sudo apt upgrade
```

2. Upgrade Python
```
sudo apt upgrade python3
```

3. Install `pip` and `venv`
```
sudo apt install python3-pip
sudo apt install python3-venv
python3 -m pip install --upgrade pip
```

## Install Open JDK 11
```bash 
sudo apt install openjdk-11-jdk
```

Check the `java` version 
```bash 
java --version
```

Find `JAVA_HOME location`
```bash 
dirname $(dirname $(readlink -f $(which java)))
```

# Mac system

## Install Homebrew 
```bash 
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## Install Open JDK 11
```bash 
brew install openjdk@11
```
Check the `java` version 
```bash 
java --version
```

# Create a virtual environment
Create a virtual environment. `python -m venv .venv`

Activate the virtual environment. `source .venv/bin/activate`

Deactivate the virtual environment. `deactivate`


# Create a virtual environment with pyenv

1. Install `Pyenv` and `python`
```bash
brew update
brew install pyenv
```

Check available Python version. `pyenv install --list`

Install python 3.11.0 by `pyenv install 3.11.0`

(Uninstall python 3.11.0 by `pyenv uninstall 3.11.0`)

2. Set up your shell environment for Pyenv
```bash
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.zshrc
echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.zshrc
echo 'eval "$(pyenv init - zsh)"' >> ~/.zshrc
```

Run `source ~/.zshrc`

See **shims** in PATH variable.
```bash
$> echo $PATH
/Users/Shinhoo/.pyenv/shims:/
```

3. Use installed Python

Check list of python versions `pyenv versions`

Set python 3.11 locally by `pyenv local 3.11.0`
```bash
$> pyenv prefix
/Users/Shinhoo/.pyenv/versions/3.11.0
```

Undo `pyenv local --unset`
```bash
$> pyenv prefix
/opt/homebrew
```

Set python 3.11 globally by `pyenv global 3.11.0`
```bash
$> pyenv prefix
/Users/Shinhoo/.pyenv/versions/3.11.0
```

Undo `pyenv global system`
```bash
$> pyenv prefix
/opt/homebrew
```

<!-- ## Reference [PyEnv](https://github.com/pyenv/pyenv) -->
