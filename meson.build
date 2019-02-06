project('lampman', 'cpp')

qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Widgets'])
inc = include_directories('include')

src_files = [ 
	'main.cpp', 
	'src/apache_config.cpp', 
	'src/conf_tree.cpp', 
	'src/lampman.cpp', 
	'src/page_cpanel.cpp', 
	'src/page_php.cpp', 
	'src/page_vhosts.cpp'
]

executable('lampman', src_files,
  include_directories: inc,
  dependencies : qt5_dep)