# How to Use GIT Repository

Date: October 8th, 2024

## 1. Generating a new SSH key and adding it to the GITHUB account
[Reference](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)

### Check if existing SSH keys are present
```bash
ls -al ~/.ssh
```
If you see the following files:
```
id_rsa.pub
id_ecdsa.pub
id_ed25519.pub
```
then, use one of them .

### Generating a new SSH key

Open `Bash` or `Zsh` and type 
```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```
If your system does not support Ed25519 algorithm, then use 
```bash
 ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
 ```

 ### Adding your SSH key to the GITHUB account

1. Open `~/.ssh/id_ed25519.pub` and copy the content. You can use 
```bash
cat ~/.ssh/id_ed25519.pub | clip
```
2. In GitHub, click your profile photo, then click `Settings`
3. Choose `SSH and GPG keys`
4. Click `New SSH key`
5. In the key field, paste your public key. 
6. Click `Add SSH key` 

## 2. Basic GIT Commands

[Reference](https://git-scm.com/docs/gittutorial#:~:text=DESCRIPTION.%20This%20tutorial%20explains%20how)
