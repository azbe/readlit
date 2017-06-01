from google import search
from lxml import html, etree
import requests
import re
import sys

if len(sys.argv) != 2:
	sys.exit(1)
searchTitle = re.sub(r'[^ \w]', '', ('goodreads ' + sys.argv[1]).lower())

urls = search(searchTitle, tld='com', lang='en', stop=1)
url = next(urls, None)

page = requests.get(url)
tree = html.fromstring(page.content)

name = re.sub(r'(^([ \n]*))|(\n)', '', tree.xpath('//h1[@class="authorName"]/span[@itemprop="name"]/text()')[0])
birth = re.sub(r'(^([ \n]*))|(\n)', '', tree.xpath('//div[@class="dataItem"][@itemprop="birthDate"]/text()')[0])
death = re.sub(r'(^([ \n]*))|(\n)', '', tree.xpath('//div[@class="dataItem"][@itemprop="deathDate"]/text()')[0])
descriptionTree = tree.xpath('//div[@class="aboutAuthorInfo"]/span')
description = re.sub(r'(&#[0-9]*;?)|(\n*<br/?>\n*)|(\n*</?[bi]>\n*)|(</?span[^>]*>)|(</?a[^>]*>)|(\n*$)', '', etree.tostring(descriptionTree[len(descriptionTree) - 1], pretty_print=True).decode('utf-8'))

print(name)
print(birth)
print(death)
print(description)
