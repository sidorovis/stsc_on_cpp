
require 'pathname'
require 'thread'

class ProtectedData
    def initialize( range, delete_files = false )
        @range_ = range
        @size = 0
        @mutex = Mutex.new
	@delete_files = delete_files
    end
    def check( s, filepath )
        if @range_.include?( s )
            @mutex.synchronize {
                @size += 1
            }
            if (@delete_files)
                File.delete( filepath )
    	    end
        end
    end
    def size
        ans = 0
        @mutex.synchronize {
            ans = @size
        }
        return ans
    end
end

$file_by_years_groups = {
    1 =>   ProtectedData.new( 0..2520, true ),
    10 =>  ProtectedData.new( 2521..10000000, false )
}
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

def start_counter
    $filenames_protecter.lock
    while !$filenames.empty? do
        filename = $filenames.pop
        puts " * Filenames to process: #{$filenames.size} : #{Time.now}" if $filenames.size % $print_each == 0
        $filenames_protecter.unlock
        
        filesize = get_lines_count( filename )
        $file_by_years_groups.each { |k,v| v.check( filesize, filename ) }
        
        $filenames_protecter.lock
    end
    $filenames_protecter.unlock
end

folder = Pathname.new("./")
folder = Pathname.new(ARGV[0]) if ARGV.size > 0

raise Exception.new( "folder #{folder} should exist") unless folder.exist?


Dir.foreach( folder ) do |item|
    next if item == '.' or item == '..'
    if /\w+\.csv/ =~ item
        fullpath = folder + item
        $filenames << fullpath
    end
end

puts "Full datafeed files size: #{$filenames.size} : #{Time.now}"    

threads_array = []

(1..thread_size).each do
    th = Thread.new do
        start_counter()
    end
    threads_array << th
end

threads_array.each { |thread| thread.join }

$file_by_years_groups.each { |k,v| puts "#{k} year datafeeds => #{v.size}" }
