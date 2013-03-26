require 'open-uri'
require 'pathname'

$check_old_files = false

folder = Pathname.new("./")
folder = Pathname.new(ARGV[0]) if ARGV.size > 0
raise Exception.new( "folder #{folder} should exist") unless folder.exist?

def get_lines_count( file_name )
    f = File.open( file_name )
    s = f.readlines.size
    s = s - 2 if s >= 2
    f.close
    return s
end

content = open( "http://www.iiroc.ca/industry/rulebook/Pages/Highly-Liquid-Stocks.aspx" ).read
links = content.scan( /<a target="_blank" href="\/Documents\/\d{4}\/[^\.]+.csv">\d{4}_\d{2}_\d{2}_HighlyLiquidStockList<\/a>/ )

links.each do |link|
	page_name = link.match( /\d{4}_\d{2}_\d{2}_HighlyLiquidStockList/ )[0].match(/\d{4}_\d{2}_\d{2}/)[0] + "_liquidity_list.csv"
	just_link = "http://www.iiroc.ca" + link.match( /\/Documents\/\d{4}\/[^\.]+.csv/ )[0]
	
	page_path = folder + page_name
	page_content = open( just_link ).read

	if ( !File.exists?( page_path ) )
		puts "saving new #{ page_path } "
		open( page_path, 'w') do |file|
			file << page_content
		end
	else
		lines_count = get_lines_count( page_path )
		if ( $check_old_files && File.size( page_path ) != (page_content.size + lines_count + 2 ) ) 
			puts "resaving #{ page_path } "
			open( page_path, 'w') do |file|
				file << page_content
			end
		end
	end
end	

puts content.scan( /<a href="javascript: __doPostBack\(/ ).size

# puts result

