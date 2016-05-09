import serial

class ProtocolReader(object):
    START_DEBUG = 0x02
    END_DEBUG = 0x03
    START_COORD = 0x16
    ACTION_DEBUG = 1
    ACTION_COORD = 2
    ACTION_UNKNO = 0

    def __init__(self, channel="/dev/ttyAMA0", baudrate=9600):
        """Initializes the ProtocolReader
        Parameters
        ----------
        channel: string
            The name of the descriptor of the serial channel
        baudrate: int 
            The UART channel baudrate
        """
        self._conn = None
        self._channel = channel
        self._baudrate = baudrate

    def __enter__(self):
        self._conn = serial.Serial(self._channel, self._baudrate)
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        if self._conn is not None:
            self._conn.close()
        return self

    def next(self):
        """Execute and print the next received action
        """
        self._validate_conn()

    def get_next_action(self):
        """Wait for the next protocol action byte and return the corresponding action constant when the byte is
        received. Consumes the action byte.
        Returns
        -------
        action: int
            Either ACTION_DEBUG, ACTION_COORD or ACTION_UNKNO according to the fetch action byte received
        """
        self._validate_conn()
        byte = self._conn.read()

        if ord(byte) == ProtocolReader.START_DEBUG:
            return ProtocolReader.ACTION_DEBUG
        elif ord(byte) == ProtocolReader.START_COORD:
            return ProtocolReader.ACTION_COORD
        else:
            print "Unknown byte : {}".format(ord(byte))
            return ProtocolReader.ACTION_UNKNO

    def print_action(self, action):
        """Execute the given action. Consumes the content of the serial line.
        Parameters
        ----------
        action: int
            Either ACTION_DEBUG, ACTION_COORD or ACTION_UNKNO according to the action to execute
        """
        if action == ProtocolReader.ACTION_COORD:
            x, y = self.get_coord()
            print "Coordinates :"
            print "X: {}".format(x)
            print "Y: {}".format(y)
            print
        elif action == ProtocolReader.ACTION_DEBUG:
            debug = self.get_debug()
            print "\n".join(["DEBUG: {}".format(line) for line in debug.split("\n")])
            print
        else:
            print "UNKNOWN ACTION !!!"

    def get_coord(self):
        """Fetch the coordinates from the serial line. The previous byte fetch should be an ACTION_COORD byte.
        Consumes the coord bytes.
        Returns
        -------
        x: int
            The x coordinate
        y: int
            The y coordinate
        """
        self._validate_conn()
        xh = ord(self._conn.read())
        xl = ord(self._conn.read())
        yh = ord(self._conn.read())
        yl = ord(self._conn.read())
        return (xh << 8) | xl, (yh << 8) | yl

    def get_debug(self):
        """Fetch the debug string from the serial line. The previous action byte read should be ACTION_DEBUG
        Consumes the debug bytes.
        Returns
        -------
        debug: string
            The debug string
        """
        self._validate_conn()
        buffer = []
        curr = self._conn.read()
        while ord(curr) != ProtocolReader.END_DEBUG:
            if ord(curr) == ProtocolReader.START_DEBUG:
                buffer = []
            else: 
                buffer.append(curr)
            curr = self._conn.read()
        return "".join(buffer)

    def _validate_conn(self):
        if self._conn is None:
            raise TypeError("Connection is not initialized.")

if __name__ == "__main__":
    with ProtocolReader("/dev/ttyAMA0", 9600) as reader:
        while True:
            action = reader.get_next_action()

            # How to fetch the data without printing it
            #if action == ProtocolReader.ACTION_COORD:
            #    x, y = reader.get_coord()
            #elif action == ProtocolReader.ACTION_DEBUG:
            #    debug_str = reader.get_debug

            reader.print_action(action)
