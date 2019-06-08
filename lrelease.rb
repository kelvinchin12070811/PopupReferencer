files = Dir.children 'langs'

files.each do | file |
    next unless file =~ /.*.ts/

    system "lrelease -compress langs/#{file}"
end