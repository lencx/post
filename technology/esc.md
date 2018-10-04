# ESC

## Install

```bash
# apt-get
sudo apt-get update
sudo apt-get upgrade

# install zsh
sudo apt-get install zsh git

ls /bin/*sh
# $(which zsh)
chsh -s /bin/zsh

# install oh-my-zsh
sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

### edit ~/.zshrc
vi ~/.zshrc
ZSH_THEME="kafeitu"
alias cls="clear"
alias ll="ls -l"
alias la="ls -a"
alias zs="source ~/.zshrc"

# public key login
ssh user@host 'mkdir -p .ssh && cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub

# install nvm
wget -qO- https://raw.githubusercontent.com/creationix/nvm/v0.33.11/install.sh | bash
```

## FileZilla

> [master password setting](https://www.ghacks.net/2017/05/26/filezilla-integrates-master-password-support/)

You can set up a master password to protect all saved passwords of FileZilla in the following way:

1. Make sure you have FileZilla 3.26.0 or higher installed on your system.
2. Open FileZilla.
3. Select Edit > Settings.
4. Switch to the Interface page.
5. There you find the passwords section. The default is set to save passwords.
6. Select "save passwords protected by a master password" from the list, and enter the desired password. It needs to have at least eight characters.
7. Select OK to save the change.