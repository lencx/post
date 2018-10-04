# [Git](https://git-scm.com/)

## Command

```bash
git init
# git add -A
git add .

# git commit -a -m "first commit" (add && commit)
git commit -m "first commit"
git remote add origin git@github.com:USERNAME/REPO.git
git pull
git push -u origin master
git push --force

git status
git diff
git merge

git reset --hard [hash]

git reflog
git commit --amend

git branch -r
git branch -r -d origin/branch-name
git push origin :branch-name

### update fork ###
# step1
git clone git@github.com:YOUR-USERNAME/YOUR-FORKED-REPO.git

# step2
cd fork-repo
git remote add upstream git://github.com/ORIGINAL-DEV-USERNAME/REPO-YOU-FORKED-FROM.git
git fetch upstream

# step3
git pull upstream master
```

### Branch

```bash
git branch
git branch -d <branchname>
# forced to delete
git branch -D <branchname>

git checkout
git checkout -b <branchname>
```

### Tags

```bash
git tag
git tag -a v1.0 -m "my version 1.0"
git show v1.0
git push origin <tagname>
git push origin --tags
# delete tag
git tag -d <tagname>
git push origin :refs/tags/<tagname>
```

## .gitconfig

```.gitconfig
[user]
      name = your_name
      email = your_email
[alias]
      st = status
      ci = commit
      co = checkout
      br = branch
      df = diff
      lg = log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit
      last = log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit -1 HEAD
[core]
      editor = emacs
```

## ssh

```bash
## authentication key generation, management and conversion
ssh-keygen -t rsa -C "email@example.com"
```

## [GitHub](https://github.com/)

* SSH key
> Settings > SSH and GPG keys > New SSH key > ~/.ssh id_rsa.pub

```bash
# git clone [url]
git init
git add -A
git commit -m "first commit"
git remote add origin git@github.com:username/repo.git
git push -u origin master
```

---

<!-- https://stackoverflow.com/questions/179123/how-to-modify-existing-unpushed-commits -->

```bash
# X is the number of commits to the last commit you want to be able to edit
git rebase -i HEAD~X

##### vim
# pick <hash> <msg>
# pick => e
e <hash> <msg>
#####

git commit --amend

##### vim
# old msg
new msg
#####

git rebase --continue
```

## Multi-user Config

```bash
# id_rsa_1 & id_rsa_1.pub
ssh-keygen -t rsa -C "your_email_1@example.com"

# id_rsa_2 & id_rsa_2.pub
ssh-keygen -t rsa -C "your_email_2@example.com"

#######################################
# vim ~/.ssh/config

Host github
    HostName github.com
    User yourName
    IdentityFile ~/.ssh/id_rsa_1

Host github2
    # other host
    # HostName gitee.com
    HostName github.com
    User yourName2
    IdentityFile ~/.ssh/id_rsa_2

#######################################

# project root path
cd ~/project/test

git config user.name "your_name";git config user.email "your_email@example.com"

# alias git2="git config user.name \"your_name\";git config user.email \"your_email@example.com\""
```
