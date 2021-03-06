#!../../virtual-env/bin/python
# daytimeJobsClean.py
# Meteor Pi, Cambridge Science Centre
# Dominic Ford

# -------------------------------------------------
# Copyright 2016 Cambridge Science Centre.

# This file is part of Meteor Pi.

# Meteor Pi is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Meteor Pi is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Meteor Pi.  If not, see <http://www.gnu.org/licenses/>.
# -------------------------------------------------

# Look up the high water mark for each daytimejobs task group, and delete any products that are newer

import os
import sys
import time

import meteorpi_db

import mod_daytimejobs
import mod_log
import mod_settings
from mod_log import log_txt


def day_time_jobs_clean(db):
    log_txt("Running daytimeJobsClean")
    cwd = os.getcwd()
    os.chdir(mod_settings.settings['dataPath'])

    obstory_list = db.get_obstory_names()

    for obstory_name in obstory_list:
        log_txt("Working on observatory <%s>" % obstory_name)

        # Clean up any file products which are newer than high water mark
        # Work on each task group in turn
        for taskGroup in mod_daytimejobs.dayTimeTasks:
            hwm_output = taskGroup[0]
            log_txt("Cleaning up products of task group <%s>" % hwm_output)
            task_list = taskGroup[2]
            if db.get_high_water_mark(obstory_name=obstory_name, mark_type=hwm_output) is None:
                db.set_high_water_mark(obstory_name=obstory_name, mark_type=hwm_output, time=0)
            high_water = db.get_high_water_mark(obstory_name=obstory_name, mark_type=hwm_output)
            for task in task_list:
                out_dirs = task[1]

                # Remove any output which is newer than HWM
                for out_dir in out_dirs:
                    for dir_name, subdir_list, file_list in os.walk(out_dir):
                        for f in file_list:
                            utc = mod_log.filename_to_utc(f)
                            if utc < 0:
                                continue
                            if utc > high_water:
                                os.system("rm -f %s" % os.path.join(dir_name, f))

    os.chdir(cwd)
    log_txt("Finished daytimeJobsClean")


# If we're called as a script, run the method exportData()
if __name__ == "__main__":
    utc_now = time.time()
    if len(sys.argv) > 1:
        utc_now = float(sys.argv[1])
    mod_log.set_utc_offset(utc_now - time.time())
    dbh = meteorpi_db.MeteorDatabase(mod_settings.settings['dbFilestore'])
    day_time_jobs_clean(dbh)
