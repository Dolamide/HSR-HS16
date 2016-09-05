# -*- coding: utf-8 -*-

# Load shared configuration
import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../.shared'))
import cfg

project = u'Recht für Ingenieure'
abbrev = 'ReIng'
author = 'Raphael Zimmermann'
version = '1.0'
release = '1.0.dev'
language = 'de'

cfg.configure()
