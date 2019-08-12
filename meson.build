project('lampman', 'cpp')

qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Widgets'])
inc = include_directories('include')

src_files = [ 
	'main.cpp', 
	'src/utils.cpp', 
	'src/server.cpp', 
	'src/lampman.cpp', 
	'src/page_cpanel.cpp', 
	'src/page_php.cpp', 
	'src/page_vhosts.cpp',
	'src/apache2/apache_config.cpp', 
	'src/apache2/vhost.cpp',
	'src/apache2/vhost_dialog.cpp',
	'src/apache2/parser/conf_node_base.cpp',
	'src/apache2/parser/conf_node.cpp',
	'src/apache2/parser/conf_tree.cpp',
	'src/apache2/parser/scanner.cpp', 
	'src/apache2/parser/parser.cpp', 
	'src/php/php_config.cpp',
]

executable('lampman', src_files,
  include_directories: inc,
  dependencies : qt5_dep)