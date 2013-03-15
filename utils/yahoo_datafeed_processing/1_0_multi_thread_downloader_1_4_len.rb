require 'open-uri'

def generate_permutations( len )
    pstart = 'a'*len
    pend = 'z'*len
    (pstart..pend).to_a
end

def processing_thread( from, to )
    th = Thread.new do
        (from..to).to_a.each do |sn|
            begin
                open( sn + ".csv", 'wb') do |file|
                    file << open('http://ichart.finance.yahoo.com/table.csv?s=' + sn).read
                end
            rescue => err
                File.delete( sn + ".csv" )
            end
        end
    end
    return th
end

thread_size = 10

(1..4).each do |l|
    thread_array = []
    ps = generate_permutations( l )
    puts "First size = #{ps.size}"
    elements_per_thread = ps.size / thread_size
    puts "Elements per thread: #{elements_per_thread}"
    size = 0
    (0..thread_size-2).each do |i|
        from = ps[ elements_per_thread * i ]
        to = ps[ elements_per_thread * ( i + 1 ) - 1 ]
        size += (from..to).to_a.size
        puts "#{from} -> #{to}" 
        thread_array << processing_thread( from, to )
    end
    from = ps[ elements_per_thread * ( thread_size-1 ) ]
    to = ps[ ps.size - 1 ]
    size += (from..to).to_a.size
    puts "#{from} -> #{to}" 
    puts "Last size = #{size}"

    thread_array << processing_thread( from, to )

    thread_array.each { |thread| thread.join }
end
