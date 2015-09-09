install:
	sudo cp static-routes /etc/network/if-up.d/static-routes
	sudo chmod 755 /etc/network/if-up.d/static-routes
	@/bin/echo -ne "\n\nRun 'sudo service network-manager restart' to commit changes\n\n"

apply:  install
	sudo service network-manager restart


uninstall:
	sudo rm /etc/network/if-up.d/static-routes



