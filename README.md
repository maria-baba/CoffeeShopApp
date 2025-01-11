# Coffee Shop Management Application  

This application is written in **C++** and utilizes **object-oriented programming (OOP)** concepts. It is designed to manage a network of coffee shops across five cities in Romania. The application assists managers in handling:  
- Employee management  
- Product inventory  
- Orders  
- Special events  
- Financial reporting  

---

## Classes  

| Class Name                | Description                             |  
|---------------------------|-----------------------------------------|  
| **Angajat (Employee)**    | Base class for employees               |  
| **Barista (Barista)**     | Derived from `Employee`                |  
| **Ospatar (Waiter)**      | Derived from `Employee`                |  
| **Manager (Manager)**     | Derived from `Employee`                |  
| **Client (Client)**       | Manages customer-related data          |  
| **Comanda (Order)**       | Handles order details and processing   |  
| **CSVHandler**            | Manages CSV file operations            |  
| **EvenimenteSpeciale**    | Handles special event details          |  
| **Produs (Product)**      | Represents products in the inventory   |  

---

## Features  

### Employee Management  
- Add employees (name, role, salary, and shifts).  
- Delete employees.  
- Modify employee shifts.  
- Display a list of all employees.  

### Product Management  
- Add new products (name, sale price, purchase price, stock units).  
- Delete products.  
- Automatically restock low-stock items.  

### Order Management  
- Place orders for multiple products.  
- Calculate total order prices, including discounts for loyal customers.  
- Update product stock after processing orders.  

### Special Event Management  
- Add special events (name, date, and cost).  
- Delete special events.  
- View a list of scheduled special events.  

### Financial Reporting  
- Generate daily financial reports with:  
- Revenue from orders and events.  
- Product costs and employee salaries.  
- Total profit.  

---
