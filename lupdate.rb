#!/usr/bin/env ruby
require 'fileutils'

tsFiles = [
    { :name => "english", :local_name => "English Global" },
    { :name => "chinese_simplified", :local_name => "简体中文" },
    { :name => "chinese_traditional",  :local_name => "繁體中文" }
]

FileUtils.mkdir 'langs' unless Dir.exist? 'langs'

tsFiles.each do | tsFile |
    system "lupdate -recursive src -ts langs/#{ tsFile[:name] }.ts"
end

langCatalogue = File.open('langs/catalogue.csv', 'w')
tsFiles.each do | lang |
    langCatalogue.puts "#{ lang[:name] },#{ lang[:local_name] }"
end

langCatalogue.close