from google import search
from lxml import html, etree
import requests
import re
import sys

if len(sys.argv) != 2:
	sys.exit(1)
searchTitle = re.sub(r'[^ \w]', '', ('merriam-webster define ' + sys.argv[1]).lower())

urls = search(searchTitle, tld='com', lang='en', stop=1)
url = next(urls, None)

page = requests.get(url)
tree = html.fromstring(page.content)

definitionList = tree.xpath('//div[@class="card-primary-content"]/ol[@class="definition-list"]/li')
definitions = []

for i in range(len(definitionList)):
	definitions.append(re.sub(r'(&#[0-9]*;?)|(\n*<br/?>\n*)|(\n*</?[bi]>\n*)|(</?span[^>]*>)|(</?[(a)(em)(p)(li)]?[^>]*>)|(\n*$)', '', re.sub(r'</?em class="vi">', 'EXAMPLE: ', etree.tostring(definitionList[i], pretty_print=True).decode('utf-8'))))
	print(definitions[i])
