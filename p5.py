import tkinter as tk

def buttonFunc():
    label_one.config(text="Shiftain Alam")

window = tk.Tk()
window.title("Show label and button widgets")
window.geometry("400x300")

#create label
label_one = tk.Label(window, text="")
label_one.place(x = 165, y = 50)

button = tk.Button(window,text="Click to reveal text",command=buttonFunc)
button.place(x = 150, y = 100)


window.mainloop()