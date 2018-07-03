# ESC

## Install

```bash
# apt-get
sudo apt-get upgrade
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