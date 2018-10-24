#!/bin/bash

set -e

date
ps axjf

#################################################################
# Update Ubuntu and install prerequisites for running Zeal   #
#################################################################
sudo apt-get update
#################################################################
# Build Zeal from source                                     #
#################################################################
NPROC=$(nproc)
echo "nproc: $NPROC"
#################################################################
# Install all necessary packages for building Zeal           #
#################################################################
sudo apt-get install -y qt4-qmake libqt4-dev libminiupnpc-dev libdb++-dev libdb-dev libcrypto++-dev libqrencode-dev libboost-all-dev build-essential libboost-system-dev libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libssl-dev libdb++-dev libssl-dev ufw git
sudo add-apt-repository -y ppa:bitcoin/bitcoin
sudo apt-get update
sudo apt-get install -y libdb4.8-dev libdb4.8++-dev

cd /usr/local
file=/usr/local/zealX
if [ ! -e "$file" ]
then
        sudo git clone https://github.com/zealproject/zealX.git
fi

cd /usr/local/zealX/src
file=/usr/local/zealX/src/zeald
if [ ! -e "$file" ]
then
        sudo make -j$NPROC -f makefile.unix
fi

sudo cp /usr/local/zealX/src/zeald /usr/bin/zeald

################################################################
# Configure to auto start at boot                                      #
################################################################
file=$HOME/.zeal
if [ ! -e "$file" ]
then
        sudo mkdir $HOME/.zeal
fi
printf '%s\n%s\n%s\n%s\n' 'daemon=1' 'server=1' 'rpcuser=u' 'rpcpassword=p' | sudo tee $HOME/.zeal/zeal.conf
file=/etc/init.d/zeal
if [ ! -e "$file" ]
then
        printf '%s\n%s\n' '#!/bin/sh' 'sudo zeald' | sudo tee /etc/init.d/zeal
        sudo chmod +x /etc/init.d/zeal
        sudo update-rc.d zeal defaults
fi

/usr/bin/zeald
echo "Zeal has been setup successfully and is running..."
exit 0

