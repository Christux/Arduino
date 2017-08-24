# Automation

Copyright (C) 2017 Christux

## Summary :

The script activates the dawn simulator for 40 minutes then turns off the lestrip.


## Installation

You can set crontab for execute the script every morning in the week for a 7H waking up:

```
#minute	hour	mday	month	wday	who	command
35  6 *	*	1,2,3,4,5	christux	/opt/sbin/sunrise.sh
```

## Keywords :

Cron, Automation, Dawn Simulator, Bash

