from hashlib import sha256

def create_hash(password): #Function taken from: https://bitbucket.org/damienjadeduff/hashing_example/raw/master/hash_password.py
    pw_bytestring = password.encode()
    return sha256(pw_bytestring).hexdigest()

def create_comment_block(topic, comment):
    template = """
        <p><b>Topic:&nbsp</b>{}<p>
        <p>{}<p>
        </br>
        </br>
        """
    return template.format(topic, comment)

password_hash = '5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8' #password: "password"
#comment_list = []
#comment_topic_list = []

comment_page_head = """
    <!DOCTYPE html>
    <html lang="en">

    <head>
        <meta charset="utf-8"/>
        <title>Future in Fiction - Discussion</title>
        <link rel="stylesheet" href="../css/style.css" />
        <link href='https://fonts.googleapis.com/css?family=Abel' rel='stylesheet'>
    </head>

    <body>

    <a href="/">
        <img class="logo" src="../images/final_logo.png" width="1100" height="397" alt="Website logo"/>
    </a>

    <ul class="nav_bar">
        <li class="nav_bar"><a href="pages/backtothefuture.html">Back to the Future Part 2</a></li>
        <li class="nav_bar"><a href="pages/bladerunner.html">Blade Runner</a></li>
        <li class="nav_bar"><a href="pages/mobilesuitgundam.html">Mobile Suit Gundam</a></li>
        <li class="nav_bar"><a href="pages/cowboybebop.html">Cowboy Bebop</a></li>
        <li class="nav_bar"><a href="pages/ghostintheshell.html">Ghost in The Shell</a></li>
        <li class="nav_bar"><a href="pages/we.html">We</a></li>
        <li class="nav_bar"><a href="/comments">Discussion</a></li>
    </ul>

    <br/>

    <article class="movie_article">

        <h1 style="font-family: 'Abel'; font-size: 50px; text-align:center;">Discussion</h1>
        <p class="home_page">Write a comment</p>

        <form action="/new_comment" method="post" id="comment_form">
            Comment: <input type="text" name="comment" size="50"/>
            &nbsp;
            Topic:
            <select name="topic" form="comment_form">
                <option value="Back to the Future Part 2">Back to the Future Part 2</option>
                <option value="Blade Runner">Blade Runner</option>
                <option value="Mobile Suit Gundam">Mobile Suit Gundam</option>
                <option value="Cowboy Bebop">Cowboy Bebop</option>
                <option value="Ghost in the Shell">Ghost in the Shell</option>
                <option value="We">We</option>
                <option value="Other">Other</option>
            </select> <br/><br/>
            Password: <input type="password" name="password"/> <br/><br/>
            <input type="submit" name="submit_button"/>
        </form>
        <br/>
"""

comment_page_tail = """
    </article>
    <div class="footer">
        <p class="footer"><br/> &nbsp;&nbsp; This website is created by Onat Şahin for BLG101E class. For HTML 5 validity of this page, <a href="https://validator.nu/?doc=https%3A%2F%2Fonatsahin-blg101-a2.herokuapp.com%2Fcomments">check this link</a>. The background image is taken from <a href="https://pngzip.com/savin-ny-website-background-web/">pngzip</a>.</p>
    </div>

    </body>

    </html>
"""

password_error_message = "<p>Invalid Password</p><br>"
