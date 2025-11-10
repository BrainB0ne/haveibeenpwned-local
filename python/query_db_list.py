import sqlite3
from Cryptodome.Hash import MD4

# Path to the input text file
file_path = "./my_passwords_list.txt" # Change this to your file location

# Connect to SQLite database
conn = sqlite3.connect("pwned_indexed")
c = conn.cursor()

# Open the text file and process each line
with open(file_path, "r", encoding="utf-8") as file:
    for line in file:
        password = line.strip() # Remove whitespace and newline characters
        if not password: # Skip empty lines
            continue

        h = MD4.new()
        h.update(password.encode('utf-16le'))

        hash = h.hexdigest().upper()

        # Search for the hash in the database
        c.execute("SELECT prevalence FROM passwords WHERE hash=?", (hash,))
        result = c.fetchone()

        if result is not None:
            prevalence = result[0] # Get the prevalence count
            print(f"Pwned! Password: {password} | NTLM: {hash} | Seen {prevalence} times.")
        else:
            print(f"Not pwned! Password: {password} | NTLM: {hash}")

        conn.commit()

# Close the database connection
conn.close()

