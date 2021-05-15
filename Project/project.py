from dataclasses import dataclass
from collections import deque

@dataclass(frozen=True, order=True)
class Process:
    index: int
    arrival: int
    burst: int
    priority: int

class Scheduler:
    def __init__(self, algorithm, time_quantum=0):
        self.algorithm = getattr(self, algorithm)
        self.time_quantum = time_quantum
        self.process_list = deque()
        self.elapsed_time = 0
    
    def add_process(self, p):
        self.process_list.append(p)
    
    def schedule(self):
        self.process_list = deque(sorted(self.process_list))
        output = self.algorithm()
    
    def FCFS(self):
        """First Come, First Serve"""
        current_process = None
        p_list = self.process_list
        next_arrival = p_list[0].arrival
        next_departure = float("inf")

        while True:
            if next_arrival <= next_departure:  # arrival, new process
                self.elapsed_time += next_arrival
                current_process = p_list.popleft()
                next_arrival = p_list[0].arrival if p_list else None
                pass

            elif next_departure < next_arrival:  # departure
                self.elapsed_time += next_departure
                pass
            
            exit_condition = next_arrival is None and next_departure is None
            if exit_condition:
                break
    
    def SJF(self):
        """Shortest Job First"""
        return
    
    def SRTF(self):
        """Shortest Remaining Time First"""
        return
    
    def P(self):
        """Priority"""
        return
    
    def RR(self):
        """Round Robin"""
        return


def main():
    num_test = int(input())

    for _ in range(num_test):
        line_1 = [i for i in input().strip().split()]

        num_process, sched_algo = line_1[:2]
        time_quantum = int(line_1[2]) if len(line_1) == 3 else 0
        scheduler = Scheduler(sched_algo, time_quantum)

        for process_index in range(1, int(num_process)+1): # index is base 1
            arrival, burst, priority = [int(i) for i in input().strip().split()]
            p = Process(process_index, arrival, burst, priority)
            scheduler.add_process(p)
        scheduler.schedule()

if __name__ == "__main__":
    main()
