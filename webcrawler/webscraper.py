import os
import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin
from collections import deque

def crawl_website(start_url, max_pages=100, max_depth=2):
    base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    data_dir = os.path.join(base_dir, "data")
    os.makedirs(data_dir, exist_ok=True)

    graph_path = os.path.join(data_dir, "var_grph.txt")
    urls_path = os.path.join(data_dir, "urls.txt")

    visited = set()
    url_to_id = {}
    edges = []
    next_id = 1

    queue = deque([(start_url, 0)])
    visited.add(start_url)
    url_to_id[start_url] = next_id
    next_id += 1

    while queue and len(visited) < max_pages:
        url, depth = queue.popleft()
        if depth >= max_depth:
            continue

        print(f"Fetching ({len(visited)}/{max_pages}): {url}")
        try:
            response = requests.get(url, timeout=5)
            html = response.text
        except Exception as e:
            print(f"❌ Failed: {e}")
            continue

        soup = BeautifulSoup(html, "html.parser")
        for a_tag in soup.find_all("a", href=True):
            link = urljoin(url, a_tag['href'])
            link = link.split('#')[0].rstrip('/')

            if link.startswith("http") and link not in visited:
                if len(visited) >= max_pages:
                    break
                visited.add(link)
                url_to_id[link] = next_id
                next_id += 1
                queue.append((link, depth + 1))

            if link in url_to_id:
                edges.append((url_to_id[url], url_to_id[link]))

    with open(graph_path, "w", encoding="utf-8") as f:
        f.write(f"{len(url_to_id)} {len(edges)}\n")
        for e in edges:
            f.write(f"{e[0]} {e[1]}\n")

    with open(urls_path, "w", encoding="utf-8") as f:
        for url, idx in url_to_id.items():
            f.write(f"{idx} {url}\n")

    print(f"\n✅ Crawled {len(visited)} pages")
    print(f"Graph saved to {graph_path}")
    print(f"URL mappings saved to {urls_path}")

if __name__ == "__main__":
    crawl_website("https://edition.cnn.com/", max_pages=300, max_depth=3)
