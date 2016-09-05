import os
import inspect
import datetime

REQUIRED_VALUES = set(['project', 'abbrev', 'author', 'version', 'release', 'language'])


def configure():
    # Load globals
    caller = inspect.stack()[1]
    cfg = caller[0].f_globals

    # Assert minimal required values are set
    missing_keys = REQUIRED_VALUES - set(cfg.keys())
    if len(missing_keys) > 0:
        raise Exception('Missing required values: %s' % list(missing_keys))

    shared_directory = os.path.abspath(os.path.dirname(__file__))

    # extensions...
    extensions = ['sphinx.ext.todo']
    if os.getenv('BUILD_PDF'):
        extensions.append('rst2pdf.pdfbuilder')
    else:
        extensions.append('sphinx.ext.imgmath')
    cfg['extensions'] = extensions

    # General config
    cfg['master_doc'] = 'index'
    cfg['source_suffix'] = '.rst'
    cfg['templates_path'] = [os.path.join(shared_directory, '_templates')]
    cfg['exclude_patterns'] = ['_build', 'Thumbs.db', '.DS_Store', 'README.rst']
    cfg['pygments_style'] = 'sphinx'
    cfg['copyright'] = u'%s, %s' % (datetime.datetime.now().year, cfg['author'])

    # HTML settings
    cfg['html_theme'] = 'alabaster'

    # rst2pdf settings
    cfg['pdf_stylesheets'] = [os.path.join(shared_directory, 'pdf_templates', 'raphael.style')]
    cfg['pdf_documents'] = [(cfg['master_doc'], cfg['abbrev'], cfg['project'], cfg['author'])]
