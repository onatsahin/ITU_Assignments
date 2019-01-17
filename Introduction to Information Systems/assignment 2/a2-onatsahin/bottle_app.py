
#####################################################################
### Assignment skeleton
### You can alter the below code to make your own dynamic website.
### The landing page for assignment 3 should be at /
#####################################################################

from bottle import route, run, default_app, debug, static_file, TEMPLATES, request, redirect
import comments

correct_password = True
comment_list = []
comment_topic_list = []

def create_comment_page():
    global correct_password
    print(comment_list)
    print(comment_topic_list)
    comment_page = comments.comment_page_head

    if not correct_password:
        comment_page += comments.password_error_message
        correct_password = True

    number_of_comments = len(comment_list)

    for i in range(number_of_comments):
        comment_page += comments.create_comment_block(comment_topic_list[i], comment_list[i])

    comment_page += comments.comment_page_tail

    return comment_page


def index():
    return static_file('index.html', root='.')

def stylesheet_callback(file_name):
    return static_file(file_name, root='./static/css/')

def image_callback(file_name):
    return static_file(file_name, root='./static/images/')

def static_page_callback(file_name):
    return static_file(file_name, root='./static/pages')

def add_new_comment():
    global correct_password

    if comments.create_hash(request.POST['password']) == comments.password_hash:
        correct_password = True
        comment_list.append(request.POST['comment'])
        comment_topic_list.append(request.POST['topic'])
    else:
        correct_password = False

    redirect('/comments')

route('/', 'GET', index)
route('/pages/<file_name>', 'GET', static_page_callback)
route('/css/<file_name>', 'GET', stylesheet_callback)
route('/images/<file_name>', 'GET', image_callback)
route('/comments', 'GET', create_comment_page)
route('/new_comment', 'POST', add_new_comment)

#####################################################################
### Don't alter the below code.
### It allows this website to be hosted on Heroku
### OR run on your computer.
#####################################################################

# This line makes bottle give nicer error messages
debug(True)
# This line is necessary for running on Heroku
app = default_app()
# The below code is necessary for running this bottle app standalone on your computer.
if __name__ == "__main__":
  run()
