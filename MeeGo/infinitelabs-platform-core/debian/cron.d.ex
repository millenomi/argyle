#
# Regular cron jobs for the infinitelabs-platform-core package
#
0 4	* * *	root	[ -x /usr/bin/infinitelabs-platform-core_maintenance ] && /usr/bin/infinitelabs-platform-core_maintenance
