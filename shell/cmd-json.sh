##########################################################################
# author: lencx <cxin1314@gmail.com>                                     #
# env: node                                                              #
# doc: https://github.com/lencx/post/tree/master/doc/shell/cmd-json      #
# homepage: https://github.com/lencx/post/blob/master/shell/cmd-json.sh  #
# more: https://github.com/antonmedv/fx                                  #
##########################################################################

# command help
help() {
  echo "    jf help:"
  echo "      jf -f <file_name> [<anonymous_function|Object_key>]     -f: local file"
  echo "      jf <url> [<anonymous_function|Object_key>]              default: url"
}

# Command-line JSON processing tool
jsonForamt() {
  if [ $1 ]; then
    if [ $1 == "-h" ]; then
      help
    elif [ $1 == "-f" ]; then
      if [ $3 ]; then
        if [ $3 =~ "=>" ]; then
          cat $2 | fx $3
        else
          cat $2 | fx "this.$3"
        fi
      else
        cat $2 | fx $3
      fi
    else
      if [ $2 ]; then
        if [ $2 =~ "=>" ]; then
          curl $1 | fx $2
        else
          curl $1 | fx "this.$2"
        fi
      else
        curl $1 | fx $2
      fi
    fi
  else
    help
  fi
}

alias jf=jsonForamt