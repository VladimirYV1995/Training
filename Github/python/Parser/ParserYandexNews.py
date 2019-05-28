import requests
from bs4 import BeautifulSoup
 
url = 'https://yandex.ru'
r = requests.get(url)
soup = BeautifulSoup(r.text, 'html.parser')
 
for link in soup.find_all('a', class_='home-link list__item-content home-link_black_yes')[:5]:
    print(link.text)
