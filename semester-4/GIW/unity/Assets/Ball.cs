using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour
{
    int frame_counter;
    public Vector3 changeScale;
    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("Hello World");
        frame_counter = 0;
    }

    // Update is called once per frame
    void Update()
    {
        transform.localScale += changeScale;
        Debug.Log("frame: " + frame_counter);
        ++frame_counter;
    }
}
