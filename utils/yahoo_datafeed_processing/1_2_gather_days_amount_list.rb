
require 'pathname'

$filenames_protecter = Mutex.new
$filenames = []

thread_size = 10
$print_each = 1000

def get_lines_count( file_name )
    f = File.open( file_name )
    s = f.readlines.size
    s = s - 2 if s >= 2
    f.close
    return s
end

folder = Pathname.new("./")
folder = Pathname.new(ARGV[0]) if ARGV.size > 0

raise Exception.new( "folder #{folder} should exist") unless folder.exist?

out = File.open( "stock_list_with_days_amount", "w" )

Dir.foreach( folder ) do |item|
    next if item == '.' or item == '..'
    if /\w+\.csv/ =~ item
        fullpath = folder + item
		out.puts "#{item},#{get_lines_count( fullpath ) }"
    end
end

out.close