#!/bin/sh

echo "connect to blabot and execute blaCtrl..."
echo ""
sshpass -p pk7svh0k ssh -t stefan@semmbox.local "pkill blaCtrl; /usr/local/bin/blaCtrl"
echo ""
echo "done"
