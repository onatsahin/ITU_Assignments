from hashlib import sha256

def create_hash(password): #Function taken from: https://bitbucket.org/damienjadeduff/hashing_example/raw/master/hash_password.py
    pw_bytestring = password.encode()
    return sha256(pw_bytestring).hexdigest()

password_hash = '89c68a38c9916aac858dfc5c995c0fa5967e821fafdfee8fe2c309e60afb9a9e'
comments = []

while True:
    new_comment = input("Enter your comment: ")
    entered_password = input("Enter your password: ")

    if password_hash == create_hash(entered_password):
        comments.append(new_comment)
        print("Previously entered comments:")
        for i in range(len(comments)):
            print("{}. {}".format(i+1, comments[i]))
    else:
        print('Invalid password')
