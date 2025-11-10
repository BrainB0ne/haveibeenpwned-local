import sqlite3
from Cryptodome.Hash import MD4

password = input("Enter your Password: ")

h = MD4.new()
h.update(password.encode('utf-16le'))

hash = h.hexdigest().upper()

#connect to DB
conn = sqlite3.connect("pwned_indexed")
c = conn.cursor()
          
#search for the hash
c.execute("SELECT prevalence FROM passwords WHERE hash=?", (hash,))
result = c.fetchone()
print("Checking: ", hash)
if result is not None:
    prevalence = result[0] # Get the prevalence count
    print(f"Pwned! This password has been seen {prevalence} times.")
else:
    print("Not pwned!")

conn.commit()
conn.close()   


