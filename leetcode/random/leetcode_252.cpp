/*
252. Meeting Rooms
Given an array of meeting time intervals where intervals[i] = [starti, endi],
 determine if a person could attend all meetings.
*/

class Solution {
    struct Sorter{
        bool operator()(const vector<int> &a, const vector<int> &b) const{
            return a[0]<b[0];
        }
    };

public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        Sorter s;
        if (intervals.size()<2) return true;
        sort(intervals.begin(),intervals.end(),s);
        int n=intervals.size();
        int latest_finish=intervals[0][1];
        for (int i=1;i<n;++i){
            int next_start=intervals[i][0];
            if (next_start<latest_finish) return false;
            latest_finish=max(latest_finish,intervals[i][1]);
        }
        
        return true;
    }
};