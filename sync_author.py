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

treeName = tree.xpath('//h1[@class="authorName"]/span[@itemprop="name"]/text()')
treeBirth = tree.xpath('//div[@class="dataItem"][@itemprop="birthDate"]/text()')
treeDeath = tree.xpath('//div[@class="dataItem"][@itemprop="deathDate"]/text()')
treeDescription = tree.xpath('//div[@class="aboutAuthorInfo"]/span')

name = re.sub(r'(^([ \n]*))|(\n)', '', treeName[0])
if treeBirth:
	birth = re.sub(r'(^([ \n]*))|(\n)', '', treeBirth[0])
else:
	birth = 'n/a'
if treeDeath:
	death = re.sub(r'(^([ \n]*))|(\n)', '', treeDeath[0])
else:
	death = 'n/a'
if treeDescription:
	description = re.sub(r'(&#[0-9]*;?)|(\n*<br/?>\n*)|(\n*</?[bi]>\n*)|(</?span[^>]*>)|(</?a[^>]*>)|(\n*$)', '', etree.tostring(treeDescription[len(treeDescription) - 1], pretty_print=True).decode('utf-8'))
else:
	description = 'n/a'

print(name)
print(birth)
print(death)
print(description)
