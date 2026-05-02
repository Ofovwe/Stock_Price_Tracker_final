# Stock_Price_Tracker_final


# Authors
- Ty Davis  
- Drew Metke  
- Ofovwe Onosode  

# Project Overview
Stock Price Tracker Final is a C++ application designed to help users track and analyze a portfolio of investment assets. The program manages multiple asset types including Stocks, ETFs, Bonds, and Cryptocurrency while calculating portfolio performance metrics.

This project demonstrates important Object-Oriented Programming concepts such as inheritance, polymorphism, encapsulation, and abstraction.

#Features
- View complete portfolio information
- Calculate total portfolio value
- Calculate total profit/loss
- Display best performing asset
- Display worst performing asset
- Save portfolio data to CSV files
- Load portfolio data from CSV files

# Technologies Used
- C++
- Object-Oriented Programming
- File Input / Output
- CSV Data Storage
- STL Containers

# Class Structure

# Base Class
**Asset**
Stores shared asset information:
- Name
- Ticker Symbol
- Current Price
- Purchase Price
- Number of Shares

# Derived Classes

**Stock**
- Sector
- Dividend Yield

**ETF**
- Expense Ratio
- Benchmark Index

**Bond**
- Interest Rate
- Years to Maturity

**Crypto**
- APY
- Staking Enabled

## Concepts Demonstrated
- Inheritance
- Virtual Functions
- Polymorphism
- Dynamic Memory Allocation
- File Handling
- Class Design
- Menu Driven Programs

## How to Run
1. Open the project in Visual Studio or another C++ IDE.
2. Build the solution.
3. Run the program.
4. Use the menu to analyze portfolio data.

## Example Menu
```text
1. View Portfolio
2. Best Performing Asset
3. Worst Performing Asset
4. Save Portfolio
5. Exit
