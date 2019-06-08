require 'fileutils'

tsFiles = [
    "english",
    "chinese_simplified",
    "chinese_traditional"
]

FileUtils.mkdir 'langs' unless Dir.exist? 'langs'

tsFiles.each do | tsFile |
    system "lupdate -recursive src -ts langs/#{ tsFile }.ts"
end