import random

def generate_ip():
    return f"{random.randint(0, 255)}.{random.randint(0, 255)}.{random.randint(0, 255)}.{random.randint(0, 255)}"

def generate_ips_list(num_ips):
    ips = [generate_ip() for _ in range(num_ips)]
    return ips

def write_ips_to_file(ips, filename):
    with open(filename, 'w') as file:
        for ip in ips:
            file.write(ip + '\n')
    file.close()

if __name__ == "__main__":
    num_ips = 1000
    ips = generate_ips_list(num_ips)
    write_ips_to_file(ips, 'ips_list.txt')