setenv LS_COLORS "di=00;34;43"
setenv LESS "--Line-numbers"
listenv
/bin/sh -c env
/bin/ls -a -l --color=always
listenv
setenv LS_STUFF "something"
setenv TEST "test"
listenv
unsetenv TEST
unsetenv LESS
listenv
/bin/ls -a -l --color=always
