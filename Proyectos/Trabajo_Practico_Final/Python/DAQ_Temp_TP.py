import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import pandas as pd

plt.style.use('ggplot')

ser = serial.Serial('COM4', 9600)

x_data = []
y_data = []
trigger_data = []
millis = 0

# Inicialmente, la gráfica está cerrada
grafica_abierta = False

# Primer eje y para la variable temperatura
figure, ax1  = plt.subplots()
line1, = ax1.plot(x_data, y_data, '-g', label="Temperatura")
ax1.set_xlabel('Time (s)')
ax1.set_ylabel('Temperatura', color=line1.get_color())
ax1.tick_params('y', colors=line1.get_color())

# Segundo eje y para la variable Trigger
ax2 = ax1.twinx()
line2, = ax2.plot(x_data, trigger_data, '-r', label='Trigger')
ax2.set_ylabel('Trigger', color=line2.get_color())
ax2.tick_params('y', colors=line2.get_color())

contador = 0
# Combinar líneas para la leyenda 
lines = [line1, line2]

def graph(frame):
    global millis, grafica_abierta    
    # Leer datos desde la placa Nucleo
    data = ser.readline().decode('utf-8').strip()
    print(data)
    # Procesar los datos si la gráfica está abierta
    if grafica_abierta:  
        if "Trigger: 0" in data and grafica_abierta:            
            grafica_abierta = False
            plt.close()                
        valores = data.split()
        print(valores)
        try:
            temp = int(valores[1])
            trigger = int(valores[3])
        except (ValueError, IndexError):
            # Ignorar los datos si no se pueden convertir a enteros o si faltan valores
            return

        x_data.append(millis)
        y_data.append(temp)
        trigger_data.append(trigger)

        # Actualizar ambas líneas 
        line1.set_data(x_data, y_data)
        line2.set_data(x_data, trigger_data)

        # Actualizar límites y vista
        ax1.relim()
        ax1.autoscale_view()

        ax2.relim()
        ax2.autoscale_view()

        millis += 1 
        #  Si se recibe 0 por elpuerto serial se cierra la grafica
    elif "Trigger: 0" in data:        
        grafica_abierta = False
        contador += 1
        plt.close()  
    return lines,

# Funcion para manejar el evento cuando se cierra la grafica
def on_close(event):
    global grafica_abierta
    grafica_abierta = False
    df = pd.DataFrame({'Time (s)': x_data, 'Temp': y_data, 'Trigger': trigger_data})
    df.to_excel('datos_temp.xlsx', index=False)
    ser.write(b'T')
    
def main(): 
    global grafica_abierta, animacion    
    animacion = FuncAnimation(figure, graph, interval=1000)     
    figure.canvas.mpl_connect('close_event', on_close)     
    while True:                
        data = ser.readline().decode('utf-8').strip()  
        print(data)            
        if "Trigger: 1" in data:                           
            grafica_abierta = True                     
            plt.show()                                              
        pass

if __name__ == "__main__":
    main()
