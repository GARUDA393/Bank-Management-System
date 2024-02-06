from flask import Flask, render_template, request, redirect, url_for
import subprocess

app = Flask(__name__)

customers = []
accounts = []


def encrypt(data): 
    return data # can use any encrypt method like b64/58... will do later

def decrypt(data):
    return data

def add_customer(name, address, phone, email, password):
    new_customer = {
        'name': name,
        'address': address,
        'phone': phone,
        'email': email,
        'password': encrypt(password)
    }
    customers.append(new_customer)
    return len(customers)

def execute_c_program(command):
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return result.stdout.decode('utf-8'), result.stderr.decode('utf-8')

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/add_customer', methods=['POST'])
def add_customer_route():
    data = request.form
    customer_id = add_customer(data['customerName'], data['address'], data['phone'], data['email'], data['password'])
    cus = data['customerName']
    print(cus)
    print("Customers:", customers)

    c_program_command = 'C:\\Users\\Admin\\Desktop\\PSC\Bank\\bank.exe'
    async def runcmd(cmd: str) -> Tuple[str, str, int, int]:
    """ run command in terminal """
    args = shlex.spli
    process = await asyncio.create_subprocess_exec(
        *args, stdout=asyncio.subprocess.PIPE, stderr=asyncio.subprocess.PIPE
    )
    stdout, stderr = await process.communicate()
    return (
        stdout.decode("utf-8", "replace").strip(),
        stderr.decode("utf-8", "replace").strip(),
        process.returncode,
        process.pid,
    )
    with subprocess.Popen(c_program_command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True) as process:
    # Prepare the input string with customer information
        input_data = 1

    # Encode the input string and send it to the program
        stdout, stderr = process.communicate(input_data.encode())

        print("Output:", stdout.decode())
        print("Error:", stderr.decode())

    message = "Record added successfully!"
    
    return redirect(url_for('success_page', message=message, customerID=customer_id, c_program_stdout=stdout.decode(), c_program_stderr=stderr.decode()))

@app.route('/success')
def success_page():
    return render_template('success.html', message=request.args.get('message'), customerID=request.args.get('customerID'), c_program_stdout=request.args.get('c_program_stdout'), c_program_stderr=request.args.get('c_program_stderr'))

if __name__ == '__main__':
    app.run(debug=True)