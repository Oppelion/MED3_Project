import xlsxwriter                                                                 # Library used for printing to documents
"""
    Method call into other python files
    from data_Collection import*
    DC = data_Collection()
"""
class data_Collection:
    """
     DC.data_AAA(name of the variable one wants to print)
    """
# /////// data collection ///////
    # All these variables are array because these needs to be looped when printing
    data_counter = []
    data_speed = []
    data_Converted_speed = []
    data_hand_distance = []
    data_converted_Hand_distance = []
    data_distance_init = []
    data_right_hand_pos = []
    data_guitar_string = []
    data_converted_distance_init = []

    def write_to_sheet(self):
        workbook = xlsxwriter.Workbook('Python.data.collection.xlsx')             # Defines the name and type of file
        worksheet_network = workbook.add_worksheet('Python.data.xlsx')            # Defines the name and type of sheet in excel

        # /////// Overview of what is being printed ///////
        # 0 - A1 counter i++
        # 1 - B1 converted initial distance
        # 2 - C1 initial distance
        # 3 - D1 Hand distance
        # 4 - E1 converted Hand distance
        # 5 - F1 converted speed
        row = 1
        column = 0
                                                                                  # Loops through all arrays to be printed and assign these to individual rows and coloumns
        for item in self.data_counter:
            worksheet_network.write('A1', 'data counter')
            worksheet_network.write(row, column, item)
            row += 1

        row = 1
        column = 1
        for item in self.data_converted_distance_init:
            worksheet_network.write('B1', ' converted initial distance')
            worksheet_network.write(row, column, item)
            row += 1

        row = 1
        column = 2
        for item in self.data_distance_init:
            worksheet_network.write('C1', 'initial distance')
            worksheet_network.write(row, column, item)
            row += 1

        row = 1
        column = 3
        for item in self.data_hand_distance:
            worksheet_network.write('D1', 'hand distance')
            worksheet_network.write(row, column, item)
            row += 1

        row = 1
        column = 4
        for item in self.data_converted_Hand_distance:
            worksheet_network.write('E1', 'converted hand distance')
            worksheet_network.write(row, column, item)
            row += 1

        row = 1
        column = 5
        for item in self.data_Converted_speed:
            worksheet_network.write('F1', 'converted speed')
            worksheet_network.write(row, column, item)
            row += 1
        workbook.close()