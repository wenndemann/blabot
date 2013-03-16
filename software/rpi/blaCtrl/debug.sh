#!/bin/sh

echo "connect to blabot and execute blaCtrl..."
echo ""
sshpass -p pk7svh0k ssh -t stefan@semmbox.local "gdbserver 192.168.178.3:10000 /usr/local/bin/blaCtrl"
echo ""
echo "done"
