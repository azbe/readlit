from google import search
from lxml import html, etree
import requests
import re
import sys

if len(sys.argv) != 2:
	sys.exit(1)
searchTitle = re.sub(r'[^ \w]', '', ('goodreads ' + sys.argv[1]).lower())

urls = search(searchTitle, tld='com', lang='en', stop=5)
url = next(urls, None)

page = requests.get(url)
tree = html.fromstring(page.content)

title = re.sub(r'(^([ \n]*))|(\n)', '', tree.xpath('//h1[@id="bookTitle"]/text()')[0])
author = re.sub(r'(^([ \n]*))|(\n)', '', tree.xpath('//div[@id="bookAuthors"]/span[@itemprop="author"]/a[@class="authorName"]/span[@itemprop="name"]/text()')[0])
description = re.sub(r'(&#[0-9]*;?)|(<br/?>)|(</?[bi]>)|(</?span[^>]*>)|(\n*$)', '', etree.tostring(tree.xpath('//div[@id="description"]/span')[1], pretty_print=True))

print 'Book Title: ', title
print 'Book Author: ', author
print 'Book Description: ', description
