#!/usr/bin/env python
#
# Copyright (c) Greenplum Inc 2009. All Rights Reserved.
#
"""

This file defines the interface that can be used to
   fetch and update system configuration information,
   as well as the data object returned by the

"""
import os

from qautils.gppylib.gplog import *
from qautils.gppylib.utils import checkNotNone
from qautils.gppylib.testold.testUtils import testOutput
from qautils.gppylib.system.osInterface import GpOsProvider

logger = get_default_logger()

class GpOsProviderForTest(GpOsProvider) :
    def __init__(self):
        pass

    def sleep(self, sleepTime):
        testOutput("Sleeping (seconds): %.2f" % sleepTime)
