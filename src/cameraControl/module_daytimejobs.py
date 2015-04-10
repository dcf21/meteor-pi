# module_daytimejobs.py
# Meteor Pi, Cambridge Science Centre
# Dominic Ford

from module_settings import *

# Define the tasks we need to do
rawH264ToTriggers = '%(binary_path)s/debug/analyseH264_libav  %(input)s %(tstamp)s %(fps)s'
rawImgToPng       = '%(binary_path)s/rawimg2png               %(input)s %(outdir)s/%(date)s/%(filename)s'
rawImgToPng3      = '%(binary_path)s/rawimg2png3              %(input)s %(outdir)s/%(date)s/%(filename)s'

if I_AM_A_RPI:
  rawVidToMp4     = '%(binary_path)s/rawvid2mp4_openmax       %(input)s /tmp/pivid_%(pid)s.h264 ; avconv -i "/tmp/pivid_%(pid)s.h264" -c:v copy -f mp4 %(outdir)s/%(date)s/%(filename)s.mp4 ; rm /tmp/pivid_%(pid)s.h264'
else:
  rawVidToMp4     = '%(binary_path)s/rawvid2mp4_libav         %(input)s %(outdir)s/%(date)s/%(filename)s.mp4'

# Nmax = maximum number of jobs which can run in parallel. NB: OpenMAX can only be used by one process at a time

#                 HWMoutput           Nmax   Folder of input files      Folder of output files                          Input ext  Shell command
dayTimeTasks = [ ['rawvideo'        , 2 , [ ['rawvideo'               ,['triggers_raw_nonlive','timelapse_raw_nonlive'],'h264', rawH264ToTriggers] ]],
                 ['triggers_rawimg' , 3 , [ ['triggers_raw_nonlive'   ,['triggers_img_processed']                      ,'rgb' , rawImgToPng],
                                            ['triggers_raw_live'      ,['triggers_img_processed']                      ,'rgb' , rawImgToPng],
                                            ['triggers_raw_nonlive'   ,['triggers_img_processed']                      ,'rgb' , rawImgToPng3],
                                            ['triggers_raw_live'      ,['triggers_img_processed']                      ,'rgb' , rawImgToPng3] ]],
                 ['triggers_rawvid' , 1 , [ ['triggers_raw_nonlive'   ,['triggers_vid_processed']                      ,'vid' , rawVidToMp4],
                                            ['triggers_raw_live'      ,['triggers_vid_processed']                      ,'vid' , rawVidToMp4] ]],
                 ['timelapse_rawimg', 3 , [ ['timelapse_raw_nonlive'  ,['timelapse_img_processed']                     ,'rgb' , rawImgToPng],
                                            ['timelapse_raw_live'     ,['timelapse_img_processed']                     ,'rgb' , rawImgToPng] ]],
               ]

