import requests
from bs4 import BeautifulSoup

url = 'https://mail.ru/'
r = requests.get(url)
soup = BeautifulSoup(r.text, 'html.parser')
 
for link in soup.find_all('a',target ='_blank')[:16]:
    print(link.text)

