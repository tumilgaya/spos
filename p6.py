import tkinter as tk

def add_traveller():
    name = name_entry.get()
    phone = phone_entry.get()
    adhaar = adhaar_entry.get()
    pickup = pickup_entry.get()
    destination = destination_entry.get()

    if(name == "" or phone == "" or adhaar == "" or pickup == "" or destination == ""):
        return

    traveller_info.append({
        "Name": name,
        "Phone": phone,
        "Adhaar": adhaar,
        "PickUp": pickup,
        "destination": destination
    })

    clearEntries()
    updateScreenList()

def clearEntries():
    name_entry.delete(0,tk.END)
    phone_entry.delete(0,tk.END)
    adhaar_entry.delete(0,tk.END)
    pickup_entry.delete(0,tk.END)
    destination_entry.delete(0,tk.END)

def updateScreenList():
    traveller_list.delete(0,tk.END)
    for idx, traveller in enumerate(traveller_info, start=1):
        traveller_list.insert(tk.END,f"Traveller {idx}: {traveller['Name']}")

app = tk.Tk()
app.title("Traveler Info")
app.geometry("400x700")

name_label = tk.Label(app,text="Name")
phone_label = tk.Label(app,text="Phone Number")
adhaar_label = tk.Label(app,text="Adhaar Number")
pickup_label = tk.Label(app,text="PickUp Location")
destination_label = tk.Label(app,text="Destination Location")

name_entry = tk.Entry(app)
phone_entry = tk.Entry(app)
adhaar_entry = tk.Entry(app)
pickup_entry = tk.Entry(app)
destination_entry = tk.Entry(app)

add_traveler_button = tk.Button(app, text = "Add traveller", command=add_traveller)
add_traveler_button.place(x = 100, y = 120)

traveller_list = tk.Listbox(app, selectmode = tk.SINGLE)
traveller_list.place(x = 100, y = 150)

#grids set
name_label.grid(row=0,column=0)
name_entry.grid(row=0,column=1)

phone_label.grid(row=1,column=0)
phone_entry.grid(row=1,column=1)

adhaar_label.grid(row=2,column=0)
adhaar_entry.grid(row=2,column=1)

pickup_label.grid(row=3,column=0)
pickup_entry.grid(row=3,column=1)

destination_label.grid(row=4,column=0)
destination_entry.grid(row=4,column=1)

traveller_info = []

app.mainloop()