require 'open-uri'

def generate_permutations( len )
    pstart = 'a'*len
    pend = 'z'*len
    (pstart..pend).to_a
end

stocks_file = File.open("_stocks","a")
bad_stocks_file = File.open("_no_stocks","a")

(1..5).each do |l|
#    ps = ('a'..'zz').to_a
    ps = generate_permutations( l )
    ps.each do |sn|
	begin
	    open( sn + ".csv", 'wb') do |file|
		file << open('http://ichart.finance.yahoo.com/table.csv?s=' + sn).read
	    end
	    puts sn+" processed"
	    stocks_file.puts( sn )
	    stocks_file.flush
	rescue => err
	    puts sn+ " was not found"
	    bad_stocks_file.puts( sn )
	    bad_stocks_file.flush
	    File.delete( sn + ".csv" )
	end
    end
end

stocks_file.close
bad_stocks_file.close
